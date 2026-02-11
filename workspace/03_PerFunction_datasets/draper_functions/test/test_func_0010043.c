multiLayerGetViewLayerID(ModelPart * modelPart, ViewLayer::ViewID viewID, ViewLayer::ViewLayerPlacement viewLayerPlacement, LayerList & layerList)
{
    if (modelPart->itemType() == ModelPart::CopperFill) {
	    if (viewLayerPlacement == ViewLayer::NewBottom) return ViewLayer::GroundPlane0;
	    else if (viewLayerPlacement == ViewLayer::NewTop) return ViewLayer::GroundPlane1;
    }


	ViewLayer::ViewLayerID wantLayer = (modelPart->flippedSMD() && viewLayerPlacement == ViewLayer::NewTop) ? ViewLayer::Copper1 : ViewLayer::Copper0;
	if (layerList.contains(wantLayer)) return wantLayer;

    return SketchWidget::multiLayerGetViewLayerID(modelPart, viewID, viewLayerPlacement, layerList);
}
