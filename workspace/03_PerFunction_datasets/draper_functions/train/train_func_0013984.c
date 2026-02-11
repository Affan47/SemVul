EditX(void)
{
	int BlockX = rintf(Me.pos.x - 0.5);
	if (BlockX < 0) {
		BlockX = 0;
		Me.pos.x = 0.51;
	}
	return BlockX;
}
