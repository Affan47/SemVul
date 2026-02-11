setup_vertical_scrollbar_default_callbacks(struct ScrollBar *pScroll)
{
  fc_assert_ret(pScroll != NULL);
  if(pScroll->pUp_Left_Button) {
    pScroll->pUp_Left_Button->action = std_up_advanced_dlg_callback;
  }
  if(pScroll->pDown_Right_Button) {
    pScroll->pDown_Right_Button->action = std_down_advanced_dlg_callback;
  }
  if(pScroll->pScrollBar) {
    pScroll->pScrollBar->action = std_vscroll_advanced_dlg_callback;
  }
}
