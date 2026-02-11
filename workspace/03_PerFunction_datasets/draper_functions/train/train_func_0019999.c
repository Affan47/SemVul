beginExecuteBlockImpl(GLESourceLine& sline, int *pcode, int *cp) {
	GLEGraphBlockInstance* graphBlock = new GLEGraphBlockInstance(this);
	begin_graph(this, graphBlock);
	return graphBlock;
}
