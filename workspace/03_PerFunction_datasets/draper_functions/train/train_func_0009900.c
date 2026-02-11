adrbk_access(PerAddrBook *pab)
{
    char       fbuf[MAXPATH+1];
    AccessType access = NoExists;
    CONTEXT_S *dummy_cntxt = NULL;

    dprint((9, "- addrbook_access -\n"));

    if(pab && pab->type & REMOTE_VIA_IMAP){


	if((pab->so = open_fcc(pab->filename, &dummy_cntxt, 1,
			       "Error: ",
			       " Can't fetch remote addrbook.")) != NULL){


	    access = MaybeRorW;
	}
    }
    else if(pab){
#if defined(NO_LOCAL_ADDRBOOKS)

	access = NoAccess;
#else
	build_path(fbuf, is_absolute_path(pab->filename) ? NULL
							 : ps_global->home_dir,
		   pab->filename, sizeof(fbuf));

#if defined(DOS) || defined(OS2)


	if(strindex(fbuf, '/') != NULL){
	    dprint((2, "\"/\" not allowed in addrbook name\n"));
	    return NoAccess;
	}
#else

	if(strindex(fbuf, '\\') != NULL){
	    dprint((2, "\"\\\" not allowed in addrbook name\n"));
	    return NoAccess;
	}
#endif

	if(can_access(fbuf, ACCESS_EXISTS) == 0){
	    if(can_access(fbuf, EDIT_ACCESS) == 0){
		char *dir, *p;

		dir = ".";
		if((p = last_cmpnt(fbuf)) != NULL){
		    *--p = '\0';
		    dir  = *fbuf ? fbuf : "/";
		}

#if	defined(DOS) || defined(OS2)


		if(isalpha((unsigned char) *dir)
		   && *(dir+1) == ':' && *(dir+2) == '\0'){
		    *(dir+2) = '\\';
		    *(dir+3) = '\0';
		}
#endif


		if(can_access(dir, EDIT_ACCESS) == 0)
		  access = ReadWrite;
		else{
		    access = ReadOnly;
		    q_status_message1(SM_ORDER, 2, 2,
				      "Address book directory (%.200s) is ReadOnly",
				      dir);
		}
	    }
	    else if(can_access(fbuf, READ_ACCESS) == 0)
	      access = ReadOnly;
	    else
	      access = NoAccess;
	}
#endif
    }

    return(access);
}
