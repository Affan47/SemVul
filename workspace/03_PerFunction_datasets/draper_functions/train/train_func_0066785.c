FindMaxRatioSum(double threshold, rapidxml::xml_document<> *doc,
                       rapidxml::xml_node<> *node) {
  if (doc == NULL || node == NULL) { return 0.0; }
  double ratio = StrToDouble(node->last_attribute(kRatio)->value());
  double max_ratio_sum = StrToDouble(node->last_attribute(kRatioSum)->value());

  if (node->first_node() == NULL && ratio >= threshold - DBL_EPSILON) {
    FindMaxRatioTag(max_ratio_sum, doc, node);
  } else if (ratio >= threshold - DBL_EPSILON) {
    for (rapidxml::xml_node<> *child = node->first_node();
         child; child = child->next_sibling()) {
      double ratio_sum = FindMaxRatioSum(threshold, doc, child);
      if (ratio_sum > max_ratio_sum) {
        max_ratio_sum = ratio_sum;
      }
    }
    FindMaxRatioTag(max_ratio_sum, doc, node);
  }

  return max_ratio_sum;
}
