iemgui_new_getnames(t_iemgui *iemgui, int indx, t_atom *argv)
{
    if (argv)
    {
        iemgui->x_snd = iemgui_new_dogetname(iemgui, indx, argv);
        iemgui->x_rcv = iemgui_new_dogetname(iemgui, indx+1, argv);
        iemgui->x_lab = iemgui_new_dogetname(iemgui, indx+2, argv);
    }
    else iemgui->x_snd = iemgui->x_rcv = iemgui->x_lab = gensym("empty");
    iemgui->x_snd_unexpanded = iemgui->x_rcv_unexpanded =
        iemgui->x_lab_unexpanded = 0;
    iemgui->x_binbufindex = indx;
    iemgui->x_labelbindex = indx + 3;
}
