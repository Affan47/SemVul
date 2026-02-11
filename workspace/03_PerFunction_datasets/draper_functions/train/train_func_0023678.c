SetAnnotationLayers(vtkAnnotationLayers* layers)
{


  if (layers != this->AnnotationLayers)
    {
    vtkAnnotationLayers *tmp = this->AnnotationLayers;
    if (tmp)
      {
      tmp->RemoveObserver(this->Observer);
      }
    this->AnnotationLayers = layers;
    if (this->AnnotationLayers != NULL)
      {
      this->AnnotationLayers->Register(this);
      this->AnnotationLayers->AddObserver(vtkCommand::ModifiedEvent,
                                        this->Observer);
      }
    if (tmp != NULL)
      {
      tmp->UnRegister(this);
      }
    this->Modified();
    this->InvokeEvent(vtkCommand::AnnotationChangedEvent, this->AnnotationLayers);
    }
}
