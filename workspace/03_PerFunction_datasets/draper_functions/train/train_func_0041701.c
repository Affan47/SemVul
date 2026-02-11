drawLabel(Renderer* renderer, bool draw_sub_labels)
{
  if ( isIntraLayerBoundary() ) return;

  if (labelData != NULL && model->getLabelDisplayFlagValue(this) ) {

    renderer->drawElementLabel(labelData->label, labelData->position);
  }

  if ( !draw_sub_labels || modelData == NULL ) {
    return;
  }

  for (int i = 0; i < modelData->nofSubElements; i++ ) {

    BodyElement* se = model->getBodyElementById((*modelData->subElementIds)[i]);

    if ( se != NULL && (se->getDrawMode() == DM_NORMAL || se->getDrawState() == DS_SELECTED) ) {
      se->drawLabel(renderer, draw_sub_labels);
    }
  }
}
