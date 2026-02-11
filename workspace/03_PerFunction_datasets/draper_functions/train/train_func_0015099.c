static_index_max (int min, int max, int origin)
{
if (origin - min > max - origin) return origin - min;

return max - origin;
}
