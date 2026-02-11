UpdateLabel()
{

  if (this->LabelVisibility)
    {
    if (this->Renderer)
      {
      this->LabelTextActor->SetCamera( this->Renderer->GetActiveCamera() );
      }
    else
      {
      vtkErrorMacro("UpdateLabel: no renderer has been set!");
      return;
      }


    double labelPosition[3], vup[3], directionOfProjection[3], xAxis[3], bounds[6];
    this->Renderer->GetActiveCamera()->GetViewUp(vup);
    this->Renderer->GetActiveCamera()->GetDirectionOfProjection(directionOfProjection);
    vtkMath::Cross( directionOfProjection, vup, xAxis );
    this->Mapper->GetBounds(bounds);
    double width = sqrt( (bounds[1] - bounds[0]) * (bounds[1] - bounds[0]) +
                         (bounds[3] - bounds[2]) * (bounds[3] - bounds[2]) +
                         (bounds[5] - bounds[4]) * (bounds[5] - bounds[4]) );
    this->GetWorldPosition(labelPosition);
    labelPosition[0] += width/2.0 * xAxis[0];
    labelPosition[1] += width/2.0 * xAxis[1];
    labelPosition[2] += width/2.0 * xAxis[2];

    this->LabelTextActor->SetPosition(labelPosition);

    if (!this->LabelAnnotationTextScaleInitialized)
      {


      this->LabelTextActor->SetScale(
          width/3.0, width/3.0, width/3.0 );
      }
    }
}
