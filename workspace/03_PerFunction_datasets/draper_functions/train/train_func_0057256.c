onApplyBasis(GtkButton *button _U_, gpointer data _U_)
{
  VisuData *dataObj;
  float matA[3][3], O[3];

  dataObj = visu_ui_rendering_window_getData(visu_ui_main_class_getDefaultRendering());
  if (setupBasisMatrix(dataObj, matA, O))
    {
      if (visu_data_setNewBasis(dataObj, matA, O))
        VISU_REDRAW_FORCE;
      else
        visu_ui_interactive_setMessage
          (_("Cannot change the basis: given matrix is singular."), GTK_MESSAGE_ERROR);
    }

  g_signal_handler_block(G_OBJECT(spinABC[0]), onSpin_id[0]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinABC[0]), 0);
  g_signal_handler_unblock(G_OBJECT(spinABC[0]), onSpin_id[0]);

  g_signal_handler_block(G_OBJECT(spinABC[1]), onSpin_id[1]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinABC[1]), 0);
  g_signal_handler_unblock(G_OBJECT(spinABC[1]), onSpin_id[1]);

  g_signal_handler_block(G_OBJECT(spinABC[2]), onSpin_id[2]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinABC[2]), 0);
  g_signal_handler_unblock(G_OBJECT(spinABC[2]), onSpin_id[2]);

  g_signal_handler_block(G_OBJECT(spinABC[3]), onSpin_id[3]);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinABC[3]), 0);
  g_signal_handler_unblock(G_OBJECT(spinABC[3]), onSpin_id[3]);

  visu_gl_ext_setActive(VISU_GL_EXT(extBasis), FALSE);
}
