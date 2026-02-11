findBoundaryCandidates()
{


  AdjacentPairArray* cp_array = new AdjacentPairArray;
  BodyElement* be1;
  BoundBox* be1_box;
  BodyElement* be2;
  BoundBox* be2_box;
  BoundBox* body2_box;
  BodyElement** be_array1;
  BodyElement** be_array2;
  int be_count1, be_count2;

  int bp_count = modelData->neighbourCandidates->size();
  BodyPair* bp;


  for (int i = 0; i < bp_count; i++) {
    bp = (*modelData->neighbourCandidates)[i];

    if (bp == NULL)
      continue;

    const Body* bd1;
    const Body* bd2;

    bp->getBodies(bd1, bd2);

    Body* body1 = (Body*) bd1;
    Body* body2 = (Body*) bd2;

    int layer1 = -1;
    while (true) {

      if (!body1->selectLayer(++layer1)) break;


      be_array1 = body1->getElementArray(layer1);
      be_count1 = body1->getElementCount(layer1);

      int layer2 = -1;
      while (true) {

        if (!body2->selectLayer(++layer2)) break;


        be_array2 = body2->getElementArray();
        be_count2 = body2->getElementCount(layer2);


        body2_box = body2->getBoundBox(layer2);
        for (int j = 0; j < be_count1; j++) {

          be1 = be_array1[j];
          be1_box = be1->getBoundBox();

          if (! be1_box->overlap(body2_box)) continue;

          for (int k = 0; k < be_count2; k++) {

            be2 = be_array2[k];
            be2_box = be2->getBoundBox();

            if (! be1_box->overlap(be2_box)) continue;

            AdjacentHalf** adj_pair = new AdjacentHalf*[2];
            adj_pair[0] = new AdjacentHalf;
            adj_pair[1] = new AdjacentHalf;
            adj_pair[0]->body = body1;
            adj_pair[0]->bodyLayer = layer1;
            adj_pair[0]->element = be1;
            adj_pair[1]->body = body2;
            adj_pair[1]->bodyLayer = layer2;
            adj_pair[1]->element = be2;
            cp_array->push_back(adj_pair);
          }
        }

        delete[] be_array2;
      }

      delete[] be_array1;
    }
  }


  return cp_array;
}
