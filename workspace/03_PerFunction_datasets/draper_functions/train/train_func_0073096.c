chatline_key_send(Widget w)
{
  String theinput;
  String empty="";

  XtVaGetValues(w, XtNstring, &theinput, NULL);

  if(*theinput) {
    send_chat(theinput);
  }

  XtVaSetValues(w, XtNstring, empty, NULL);
}
