findInnerBoundaries()
{
  IdArray swap1_ids;
  IdArray swap2_ids;
  IdArray relative_dirs;

  int count = modelData->boundaryCandidates->size();

  for (int i = 0; i < count; i++) {

    AdjacentHalf** adj_pair = (*modelData->boundaryCandidates)[i];

    if (adj_pair == NULL)
      continue;

    BodyElement* be1 = adj_pair[0]->element;
    BodyElement* be2 = adj_pair[1]->element;
    BodyElement* common = NULL;

    matchType match_type = be1->findCommonBoundary(be2, common);

    if (match_type != MATCH_NONE) {


      Body* b1 = adj_pair[0]->body;
      Body* b2 = adj_pair[1]->body;
      int lr1  = adj_pair[0]->bodyLayer;
      int lr2  = adj_pair[1]->bodyLayer;

      b1->incrBndrCount(lr1, INNER_ELEMENT);
      b2->incrBndrCount(lr2, INNER_ELEMENT);


      switch (match_type) {
      case MATCH_1_INSIDE:
        be2->addCoveringElement(common, BE_INNER);
        break;
      case MATCH_2_INSIDE:
        be1->addCoveringElement(common, BE_INNER);
        break;
      case MATCH_OVERLAP:
        be1->addCoveringElement(common, BE_INNER);
        be2->addCoveringElement(common, BE_INNER);
        break;
      case MATCH_EXACT:
        be1->addStatus(BE_INNER);
        be2->addStatus(BE_INNER);
        b1->swapBodyElements(lr1, be1, common);
        b2->swapBodyElements(lr2, be2, common);

        if ( be1 == common) {
          swap1_ids.push_back(be2->Id());
        } else {
          swap1_ids.push_back(be1->Id());
        }

        swap2_ids.push_back(common->Id());

        relative_dirs.push_back(getRelativeOrientation(be1, be2));
        break;
      }

    }

  }

  if ( swap1_ids.size() > 0 ) {
    swapBodyElements(&swap1_ids, &swap2_ids, &relative_dirs);
  }

}
