AddWidget( vtkAbstractWidget *w )
{
  for ( unsigned int i = 0; i < this->Widget.size(); i++)
    {
    if (this->Widget[i] == w)
      {
      return;
      }
    }

  this->Widget.push_back(w);
  w->Register(this);


  static_cast<vtkParallelopipedWidget*>(w)->WidgetSet = this;
}
