mpi_sche_write_set_loop_param(fsbe_context *cx, Hmdf_table *hmdf)
{
    Module_table *module = hmdf->block->module;
    Block *block = hmdf->block;
    Statement *stm;
    Quadruple *qr;

    if( module->nt_elem_head == NULL)
	return;

    if( block->kind == LOOP || block->kind == DOALL ||
	block->kind == DOACR || block->kind == DOSUM){
	for( stm = block->pre_head->stm_head; stm != NULL; stm = stm->next){
	    if( stm->ope == OPE_DO){
		for( qr = stm->qr_head; qr->ope != OPE_DO; qr = qr->next);

		cx->module = module;
		fsbe_printf(cx, "if( msp->first_init_flg == TRUE){\n");
		fsbe_printf(cx, "    ");
		sbe_write_operand(cx, qr->op[0]);
		fsbe_printf(cx, " = ");
		sbe_write_operand(cx, qr->op[1]);
		fsbe_printf(cx, ";\n");
		fsbe_printf(cx, "    msp->first_loop_flg = TRUE;\n");
		fsbe_printf(cx, "    msp->first_init_flg = FALSE;\n");
		fsbe_printf(cx, "}else{\n");
		fsbe_printf(cx, "    ");
		sbe_write_operand(cx ,qr->op[0]);
		fsbe_printf(cx, " += ");
		sbe_write_operand(cx, qr->op[3]);
		fsbe_printf(cx, ";\n");
		fsbe_printf(cx, "    msp->first_loop_flg = FALSE;\n");
		fsbe_printf(cx, "}\n");
	    }
	}
    }
}
