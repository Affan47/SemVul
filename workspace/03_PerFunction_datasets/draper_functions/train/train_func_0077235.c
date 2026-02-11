make_sfun(object name, object (*self)(), int argd, object data)


{object sfn;

	sfn = alloc_object(t_sfun);
        if(argd >15) sfn->d.t = (int)t_gfun;
	sfn->sfn.sfn_self = self;
	sfn->sfn.sfn_name = name;
	sfn->sfn.sfn_data = data;
        sfn->sfn.sfn_argd = argd;
	return(sfn);
}
