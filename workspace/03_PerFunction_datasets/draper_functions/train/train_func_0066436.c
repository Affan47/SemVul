testScapegoatTree(void)
{
	TreeMap *tree = iTreeMap.Create(sizeof(double));
	TreeMap *tree1 = iTreeMap.Create(sizeof(double));
	double d = 1.0;
	size_t i;

	iTreeMap.SetCompareFunction(tree,compareDoubles);
	for (i=0; i<MAX_IT;i++) {
		d = i+1;
		iTreeMap.Add(tree,&d,NULL);
	}
	if (iTreeMap.Size(tree) != i)
		Abort();
	iTreeMap.Apply(tree,printDoubleTree,stdout);
	printf("Size: %lu\n", (long unsigned)iTreeMap.Sizeof(tree));
	iTreeMap.SetCompareFunction(tree1,compareDoubles);
	for (i=0; i<MAX_IT;i++) {
		d = i+1;
		iTreeMap.Add(tree1,&d,NULL);
	}
#if 0
	if (!iTreeMap.Equal(tree1,tree))
		printf("Error in comparison of binary search trees\n");
#endif
	d = 2.0;
	iTreeMap.Erase(tree,&d,NULL);
	iTreeMap.Apply(tree,printDoubleTree,stdout);
	iTreeMap.Finalize(tree);
	iTreeMap.Finalize(tree1);
}
