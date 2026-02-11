try_combine_classifiers(RouterT *router, ElementT *classifier)
{
  ElementClassT *classifier_t = ElementClassT::base_type("Classifier");
  if (classifier->type() != classifier_t)

    return false;

  Vector<PortT> branches;
  router->find_connections_to(PortT(classifier, 0), branches);
  for (int i = 0; i < branches.size(); i++)
    if (branches[i].element->type() == classifier_t) {

      if (combine_classifiers(router, branches[i].element, branches[i].port, classifier)) {
	try_combine_classifiers(router, classifier);
	return true;
      }
    }

  return false;
}
