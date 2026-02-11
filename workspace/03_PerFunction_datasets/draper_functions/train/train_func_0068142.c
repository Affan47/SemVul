ED4_createVisualizeSAI_Awars(AW_root *aw_root, AW_default aw_def) {
    aw_root->awar_int   (AWAR_SAI_ENABLE,                 0,  aw_def);
    aw_root->awar_int   (AWAR_SAI_ALL_SPECIES,            0,  aw_def);
    aw_root->awar_int   (AWAR_SAI_AUTO_SELECT,            0,  aw_def);
    aw_root->awar_string(AWAR_SAI_SELECT,                 "", aw_def);
    aw_root->awar_string(AWAR_SAI_CLR_TRANS_TABLE,        "", aw_def);
    aw_root->awar_string(AWAR_SAI_CLR_TRANS_TAB_NEW_NAME, "", aw_def);
    aw_root->awar_string(AWAR_SAI_CLR_TRANS_TAB_NAMES,    "", aw_def);

    for (int i=0;i<10;i++){
       AW_awar *def_awar = aw_root->awar_string(getAwarName(i),"",aw_def);
       def_awar->add_callback(colorDefChanged_callback, (AW_CL)i);
    }
    aw_root->awar(AWAR_SAI_ENABLE)->add_callback(setVisualizeSAI_cb);
    aw_root->awar(AWAR_SAI_ALL_SPECIES)->add_callback(setVisualizeSAI_options_cb);
    aw_root->awar(AWAR_SAI_AUTO_SELECT)->add_callback(set_autoselect_cb);
    aw_root->awar(AWAR_SAI_SELECT)->add_callback(saiChanged_callback);
    aw_root->awar(AWAR_SAI_CLR_TRANS_TABLE)->add_callback(colorDefTabNameChanged_callback);

    ED4_ROOT->visualizeSAI            = aw_root->awar(AWAR_SAI_ENABLE)->read_int();
    ED4_ROOT->visualizeSAI_allSpecies = aw_root->awar(AWAR_SAI_ALL_SPECIES)->read_int();


    AW_awar *awar_defaults_created = aw_root->awar_int(AWAR_SAI_CLR_DEFAULTS_CREATED, 0,  aw_def);

    if (awar_defaults_created->read_int() == 0) {
        addDefaultTransTable(aw_root, "numeric",   "0;1;2;3;4;5;6;7;8;9;");
        addDefaultTransTable(aw_root, "binary",    ".;+;;;;;;;;;");
        addDefaultTransTable(aw_root, "consensus", "=ACGTU;;acgtu;.;;;;;;;");
        addDefaultTransTable(aw_root, "helix",     ";;<>;;;;;[];;;");
        addDefaultTransTable(aw_root, "xstring",   ";x;;;;;;;;;");
        addDefaultTransTable(aw_root, "gaps",      ";-.;;;;;;;;;");

        awar_defaults_created->write_int(1);
    }

    inCallback = true;
    saiChanged_callback(aw_root);
    colorDefTabNameChanged_callback(aw_root);
    set_autoselect_cb(aw_root);
    inCallback = false;
}
