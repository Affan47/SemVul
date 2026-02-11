knh_write_cid(CTX ctx, kOutputStream *w, kclass_t cid)
{
	const char *tname = NULL;
	switch(cid) {
	case TYPE_dynamic:  tname = "dynamic";    break;
	case TYPE_void: tname = "void";       break;
	case TYPE_var:  tname = "var";        break;
	case TYPE_This: tname = "This";       break;
	default :{
			if(cid > TYPE_This) {
				knh_write(ctx, w, STEXT("T"));
				knh_write_ifmt(ctx, w, KINT_FMT, cid - TYPE_This);
			}
			else {
				knh_write(ctx, w, S_tobytes(ClassTBL(cid)->lname));
			}
			return ;
		}
	}
	knh_write_ascii(ctx, w, tname);
}
