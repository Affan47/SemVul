checkMeshElement(meshElementCode element_code, int* node_ids, bool swap_to_ccw)
{
  bool result;
  switch (element_code) {
  case MEC_303:
  case MEC_304:
    result = checkMeshElement303(node_ids, swap_to_ccw);
    break;
  case MEC_306:
  case MEC_307:
    result = checkMeshElement306(node_ids, swap_to_ccw);
    break;
  case MEC_404:
    result = checkMeshElement404(node_ids, swap_to_ccw);
    break;
  case MEC_408:
  case MEC_409:
    result = checkMeshElement408(node_ids, swap_to_ccw);
    break;
  case MEC_504:
    result = checkMeshElement504(node_ids, swap_to_ccw);
    break;
  case MEC_508:
    result = checkMeshElement508(node_ids, swap_to_ccw);
    break;
  case MEC_510:
    result = checkMeshElement510(node_ids, swap_to_ccw);
    break;
  case MEC_808:
    result = checkMeshElement808(node_ids, swap_to_ccw);
    break;
  case MEC_820:
    result = checkMeshElement820(node_ids, swap_to_ccw);
    break;
  default:
    break;
  }

  return result;
}
