endioctl(Void)
{
	int i;
	expptr p;
	struct io_setup *ios;

	inioctl = NO;


	ioerrlab = ioendlab = skiplab = jumplab = 0;

	if(p = V(IOSEND))
		if(ISICON(p))
			execlab(ioendlab = p->constblock.Const.ci);
		else
			err("bad end= clause");

	if(p = V(IOSERR))
		if(ISICON(p))
			execlab(ioerrlab = p->constblock.Const.ci);
		else
			err("bad err= clause");

	if(IOSTP)
		if(IOSTP->tag!=TADDR || ! ISINT(IOSTP->addrblock.vtype) )
		{
			err("iostat must be an integer variable");
			frexpr(IOSTP);
			IOSTP = NULL;
		}

	if(iostmt == IOREAD)
	{
		if(IOSTP)
		{
			if(ioerrlab && ioendlab && ioerrlab==ioendlab)
				jumplab = ioerrlab;
			else
				skiplab = jumplab = newiolabel();
		}
		else	{
			if(ioerrlab && ioendlab && ioerrlab!=ioendlab)
			{
				IOSTP = (expptr) mktmp(TYINT, ENULL);
				skiplab = jumplab = newiolabel();
			}
			else
				jumplab = (ioerrlab ? ioerrlab : ioendlab);
		}
	}
	else if(iostmt == IOWRITE)
	{
		if(IOSTP && !ioerrlab)
			skiplab = jumplab = newiolabel();
		else
			jumplab = ioerrlab;
	}
	else
		jumplab = ioerrlab;

	endbit = IOSTP!=NULL || ioendlab!=0;
	errbit = IOSTP!=NULL || ioerrlab!=0;
	if (jumplab && !IOSTP)
		IOSTP = (expptr) mktmp(TYINT, ENULL);

	if(iostmt!=IOREAD && iostmt!=IOWRITE)
	{
		ios = io_stuff + iostmt;
		io_fields = ios->fields;
		ioblkp = io_structs[iostmt];
		if(ioblkp == NULL)
			io_structs[iostmt] = ioblkp =
				autovar(1, ios->type, ENULL, "");
		ioset(TYIOINT, XERR, ICON(errbit));
	}

	switch(iostmt)
	{
	case IOOPEN:
		dofopen();
		break;

	case IOCLOSE:
		dofclose();
		break;

	case IOINQUIRE:
		dofinquire();
		break;

	case IOBACKSPACE:
		dofmove("f_back");
		break;

	case IOREWIND:
		dofmove("f_rew");
		break;

	case IOENDFILE:
		dofmove("f_end");
		break;

	case IOREAD:
	case IOWRITE:
		startrw();
		break;

	default:
		fatali("impossible iostmt %d", iostmt);
	}
	for(i = 1 ; i<=NIOS ; ++i)
		if(i!=IOSIOSTAT && V(i)!=NULL)
			frexpr(V(i));
}
