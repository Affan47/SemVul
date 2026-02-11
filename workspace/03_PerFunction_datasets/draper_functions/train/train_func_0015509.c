pop()
{
    depth--;

    for (int i = 0; i < NumStacks; i++)
	while (stacks[i] != NULL && stacks[i]->depth > depth)
	    popElement((StackIndex) i);
}
