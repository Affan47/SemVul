visu_rendering_createNode(VisuRendering *method, VisuData *data,
                               VisuNode *node, VisuElement *ele, int eleGlId)
{
  g_return_if_fail(VISU_IS_RENDERING_TYPE(method));


  if (!ele)
    ele = visu_node_array_getElement(VISU_NODE_ARRAY(data), node);
  if (eleGlId == -1)
    eleGlId = visu_rendering_getElementGlId(method, ele);


  VISU_RENDERING_GET_CLASS(method)->createNode(data, node, ele, eleGlId);
}
