dglTreeNode2Cancel(void *pvNode2, void *pvParam)
{
    if (((dglTreeNode2_s *) pvNode2)->pv)
	free(((dglTreeNode2_s *) pvNode2)->pv);
    if (((dglTreeNode2_s *) pvNode2)->pv2)
	free(((dglTreeNode2_s *) pvNode2)->pv2);
    if (((dglTreeNode2_s *) pvNode2)->pv3)
	free(((dglTreeNode2_s *) pvNode2)->pv3);
    free(pvNode2);
}
