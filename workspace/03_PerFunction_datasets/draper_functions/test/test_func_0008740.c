parse_titleblock(int fd)
{
    int size,sheet,total,ypos;
    char localbuf[1000];
    char data[100];
    char pagesize;

    size = read_block(fd,localbuf,5,sizeof(localbuf));


    sheet=CONV16(localbuf,0x00);
    total=CONV16(localbuf,0x02);
    fprintf(stderr,"Sheet #%d of %d\n",sheet,total);
    read_string(data,sizeof(data),localbuf+DATE);
    fprintf(stderr,"%s\n",data);

    switch(localbuf[4] && 0x0F)
    {
	case 0: pagesize = 'A'; ypos = 8*scale+scale/2; break;
	case 1: pagesize = 'B'; ypos = 11*scale; break;
	case 2: pagesize = 'C'; ypos = 17*scale; break;
	case 3: pagesize = 'D'; ypos = 22*scale; break;
	case 4: pagesize = 'E'; ypos = 34*scale; break;
	default:  fprintf(stderr,"Unknown Page Size\n");exit(-1);
    }
    if (scale==100) {
	fprintf(stdout,"C %d %d 0 0 0 title-%c.sym\n",CONVX(0),CONVY(ypos),pagesize);
    }
}
