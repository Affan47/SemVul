long_output_click(GtkWidget *w, struct model_pak * model)
{
    if (model->siesta.long_output)
    {
        model->siesta.file_output_write_coor_step = TRUE;
        model->siesta.file_output_write_forces = TRUE;
        model->siesta.file_output_write_kpoints = TRUE;
        model->siesta.file_output_write_eigenvalues = TRUE;
        model->siesta.file_output_write_bands = TRUE;
        model->siesta.file_output_write_kbands = TRUE;
        model->siesta.file_output_write_wavefunctions = TRUE;
        model->siesta.file_output_write_mullikenpop = 1;
        gui_relation_update(NULL);
    }
    else
    {
        model->siesta.file_output_write_coor_step = FALSE;
        model->siesta.file_output_write_forces = FALSE;
        model->siesta.file_output_write_kpoints = FALSE;
        model->siesta.file_output_write_eigenvalues = FALSE;
        model->siesta.file_output_write_bands = FALSE;
        model->siesta.file_output_write_kbands = FALSE;
        model->siesta.file_output_write_wavefunctions = FALSE;
        model->siesta.file_output_write_mullikenpop = 0;
        gui_relation_update(NULL);
    }
}
