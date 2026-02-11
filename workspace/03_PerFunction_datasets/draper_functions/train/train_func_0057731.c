stop_compare_mode()
{


  if(test_compare_mode())
  {
    tmrl->clear_compare_event ( ccpcon );
  }
  ccpcon = 0;
}
