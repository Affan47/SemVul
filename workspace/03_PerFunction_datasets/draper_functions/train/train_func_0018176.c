Transform (const R3Transformation& transformation)
{

    if (IsEmpty()) return;


    R3Box tmp = R3null_box;
    for (RNOctant octant = 0; octant < RN_NUM_OCTANTS; octant++) {
	R3Point corner(Corner(octant));
	corner.Transform(transformation);
	tmp.Union(corner);
    }
    *this = tmp;
}
