AddBalloon(vtkProp *prop, vtkStdString *str,
                                  vtkImageData *img)
{
  vtkPropMapIterator iter = this->PropMap->find(prop);
  if ( iter == this->PropMap->end() || (*this->PropMap)[prop] != vtkBalloon(str,img) )
    {
    (*this->PropMap)[prop] = vtkBalloon(str,img);
    if ( prop != NULL )
      {
      this->Picker->DeletePickList(prop);
      this->Picker->AddPickList(prop);
      }
    this->Modified();
    }
}
