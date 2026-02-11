e_grabinput_focus(Ecore_X_Window win, E_Focus_Method method)
{
   if (grab_key_win != 0)
     {

        focus_win = win;
        focus_method = method;
     }
   else
     {

        _e_grabinput_focus(win, method);
     }
}
