reload_ecoli(const SEC_dbcb *cb) {
    GB_transaction ta(gb_main);

    delete ecoli_seq;
    delete Ecoli;

    GBDATA *gb_ecoli = GBT_find_SAI(gb_main,"ECOLI");
    if (gb_ecoli) {
        ecoli_seq = new SEC_seq_data(gb_ecoli, aliname, cb);
        Ecoli = new BI_ecoli_ref;

        GB_ERROR error = Ecoli->init(ecoli_seq->sequence(), ecoli_seq->length());
        if (error) {
            error = ta.close(error);
            aw_message(error);
        }
    }
    else {
        ecoli_seq = 0;
        Ecoli     = 0;
    }

    gfx->request_update(SEC_UPDATE_SHOWN_POSITIONS);
    if (perform_refresh) ntw->refresh();
}
