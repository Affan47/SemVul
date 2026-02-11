localize_bundle_as_shell (struct fnarg *arg,
				     fn_param *fp)
{
    int err = 0;

    err = arg_add_as_shell(fp->name, GRETL_TYPE_BUNDLE, arg->val.b);

    if (!err) {
	arg->name = fp->name;
    }

    return err;
}
