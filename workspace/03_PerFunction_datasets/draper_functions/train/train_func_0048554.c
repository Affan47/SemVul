write_attr(struct ng_attribute *attr, int value)
{
    switch (attr->id) {
    case 1000:
	parm_k = value;
	break;
    case 1001:
	parm_zoom = value;
	break;
    case 1002:
	parm_cx = value;
	break;
    case 1003:
	parm_cy = value;
	break;
    }
}
