read_dict(struct dict_radix *dict, const char *dir)
{
	if(dir){
		FILE *fp;
		char s[1024];
		int small,medium,full,ret;
#ifdef PREFIX_FILE
		FILE *prefixes;
#endif

		snprintf(s,sizeof(s),"%s.sizes",dir);
		if(!(fp=fopen(s,"r"))){
			fprintf(stderr,"Hspell: can't open %s.\n",s);
			return 0;
		}
		if(fscanf(fp,"%d %d %d",&small,&medium,&full)!=3){
			fprintf(stderr,"Hspell: can't read from %s.\n",s);
			return 0;
		}
		fclose(fp);

#ifdef HAVE_ZLIB
		if(!(fp=gzopen(dir,"r"))){
			fprintf(stderr,"Hspell: can't open %s.\n",dir);
			return 0;
		}
#else
		snprintf(s,sizeof(s),"gzip -dc '%s'",dir);
		if(!(fp=popen(s,"r"))){
			fprintf(stderr,"Hspell: can't run %s.\n",s);
			return 0;
		}
#endif

#ifdef PREFIX_FILE
#ifdef HAVE_ZLIB
		snprintf(s,sizeof(s),"%s.prefixes",dir);
		if(!(prefixes=gzopen(s,"rb"))){
			fprintf(stderr,"Hspell: can't open %s.\n",s);
			return 0;
		}
#else
		snprintf(s,sizeof(s),"gzip -dc '%s.prefixes'",dir);
		if(!(prefixes=popen(s,"rb"))){
			fprintf(stderr,"Hspell: can't run %s.\n",s);
			return 0;
		}
#endif
#endif

		allocate_nodes(dict,small,medium,full);
#ifdef PREFIX_FILE
		ret=do_read_dict(fp, prefixes, dict);
		pclose(prefixes);
#else
		ret=do_read_dict(fp, dict);
#endif
		pclose(fp);
		return ret;
	} else {
#ifdef HAVE_ZLIB

		FILE *in=gzdopen(fileno(stdin),"r");
#ifdef PREFIX_FILE
		FILE *zero=gzopen("/dev/zero","r");
#endif
#else
		FILE *in=stdin;
#ifdef PREFIX_FILE
		FILE *zero=fopen("/dev/zero","r");
#endif
#endif

#ifdef PREFIX_FILE
		return do_read_dict(in, zero, dict);
#else
		return do_read_dict(in, dict);
#endif
	}
}
