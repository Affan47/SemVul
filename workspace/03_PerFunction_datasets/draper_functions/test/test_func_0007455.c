csbe_write_var_init(cx, vp)
    csbe_context *cx;
    Var_table *vp;
{
    Data_table *dp;

    for(dp = cx->data_head; dp; dp = dp->next){
        if( dp->op->entry == vp->entry && dp->op->kind == KIND_VAR){
            csbe_printf(cx, " = ");
	    csbe_write_data_node_member(cx, dp->node_head, vp->type, vp->type_entry);
        }
    }
}
