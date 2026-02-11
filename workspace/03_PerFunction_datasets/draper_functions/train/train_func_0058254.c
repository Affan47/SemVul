eval(SeVec3d& result) const
{

    SeVec3d val;
    child(0)->eval(val);
    if (val[0])
	child(1)->eval(val);
    else
	child(2)->eval(val);
    result = 0.0;
}
