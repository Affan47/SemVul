H5S_point_iter_has_next_block(const H5S_sel_iter_t *iter)
{
    htri_t ret_value=TRUE;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(iter);


    if(iter->u.pnt.curr->next==NULL)
        HGOTO_DONE(FALSE);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
