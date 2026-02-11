create_gene_extract_window(AW_root *root, AW_CL cl_pmode)
{
    AW_window_simple *aws       = new AW_window_simple;
    string            window_id = performmode_relative_id("EXTRACT_GENE", GEN_PERFORM_MODE(cl_pmode));

    aws->init(root, window_id.c_str(), "Extract genes to alignment");
    aws->load_xfig("ad_al_si.fig");

    aws->callback( (AW_CB0)AW_POPDOWN);
    aws->at("close");
    aws->create_button("CLOSE","CLOSE","C");

    aws->at("label");
    aws->create_autosize_button(0,"Please enter the name\nof the alignment to extract to");

    aws->at("input");
    aws->create_input_field(AWAR_GENE_EXTRACT_ALI,15);

    aws->at("ok");
    aws->callback(gene_extract_cb, cl_pmode);

    aws->create_button("GO", "GO", "G");

    return aws;
}
