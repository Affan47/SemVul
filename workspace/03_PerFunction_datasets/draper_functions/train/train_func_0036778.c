ModifyTerrainLair(int t, int i, int l)
{
	if(t < 0 || t > (R_NUM -1)) return;
	if(i < 0 || i >= (int)(sizeof(TerrainDefs[t].lairs)/sizeof(int))) return;
	if(l < -1 || l > NOBJECTS-1) l = -1;
	TerrainDefs[t].lairs[i] = l;
}
