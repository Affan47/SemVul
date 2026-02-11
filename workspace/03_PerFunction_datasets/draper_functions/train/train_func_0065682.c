expand_dist_map(array_2d<edist>& dists)
{
	const unsigned int width(dists.width);
	const unsigned int height(dists.height);
	const unsigned int size(dists.size);


	for(int i = 0; i < size; i++)
	{
		if((i % width)) dists[i].choose(dists[i - 1].right());
		if(i > width) dists[i].choose(dists[i - width].below());
	}


	for(int i = size - 1; i >= 0; i--)
	{
		if((i % width) + 1 < width) dists[i].choose(dists[i + 1].left());
		if((i + width) < size) dists[i].choose(dists[i + width].above());
	}


	for(int x = width - 1; x >= 0; x--)
	for(int y = 0; y < height; y++)
	{
		int i = x + y * width;
		if((i % width) + 1 < width) dists[i].choose(dists[i + 1].left());
		if(i > width) dists[i].choose(dists[i - width].below());
	}


	for(int x = 0; x < width; x++)
	for(int y = height - 1; y >= 0; y--)
	{
		int i = x + y * width;
		if((i % width)) dists[i].choose(dists[i - 1].right());
		if((i + width) < size) dists[i].choose(dists[i + width].above());
	}

}
