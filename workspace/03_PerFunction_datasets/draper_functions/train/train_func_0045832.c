change_existing_project_attributes(project_ty *pp, pattr_ty *pattr_data)
{
    user_ty::pointer up;


    up = user_ty::create();


    pp->pstate_lock_prepare();
    lock_take();


    check_permissions(pp, up);


    project_pattr_set(pp, pattr_data);

    pp->pstate_write();
    commit();
    lock_release();
    project_verbose(pp, 0, i18n("project attributes complete"));
}
