testInterpolation()
{
	bool result=true;
	core::quaternion q(1.f,2.f,3.f,4.f);
	core::quaternion q2;
	q2.lerp(q,q,0);
	if (q != q2)
	{
		logTestString("Quaternion lerp with same quaternion did not yield same quaternion back (with t==0).\n");
		result = false;
	}
	q2.lerp(q,q,0.5f);
	if (q != q2)
	{
		logTestString("Quaternion lerp with same quaternion did not yield same quaternion back (with t==0.5).\n");
		result = false;
	}
	q2.lerp(q,q,1);
	if (q != q2)
	{
		logTestString("Quaternion lerp with same quaternion did not yield same quaternion back (with t==1).\n");
		result = false;
	}
	q2.lerp(q,q,0.2345f);
	if (q != q2)
	{
		logTestString("Quaternion lerp with same quaternion did not yield same quaternion back (with t==0.2345).\n");
		result = false;
	}
	q2.slerp(q,q,0);
	if (q != q2)
	{
		logTestString("Quaternion slerp with same quaternion did not yield same quaternion back (with t==0).\n");
		result = false;
	}
	q2.slerp(q,q,0.5f);
	if (q != q2)
	{
		logTestString("Quaternion slerp with same quaternion did not yield same quaternion back (with t==0.5).\n");
		result = false;
	}
	q2.slerp(q,q,1);
	if (q != q2)
	{
		logTestString("Quaternion slerp with same quaternion did not yield same quaternion back (with t==1).\n");
		result = false;
	}
	q2.slerp(q,q,0.2345f);
	if (q != q2)
	{
		logTestString("Quaternion slerp with same quaternion did not yield same quaternion back (with t==0.2345).\n");
		result = false;
	}
	core::quaternion q3(core::vector3df(45,135,85)*core::DEGTORAD);
	q.set(core::vector3df(35,125,75)*core::DEGTORAD);
	q2.slerp(q,q3,0);
	if (q != q2)
	{
		logTestString("Quaternion slerp with different quaternions did not yield first quaternion back (with t==0).\n");
		result = false;
	}
	q2.slerp(q,q3,1);
	if (q3 != q2)
	{
		logTestString("Quaternion slerp with different quaternions did not yield second quaternion back (with t==1).\n");
		result = false;
	}
	q2.slerp(q,q3,0.5);
	if (!q2.equals(core::quaternion(-0.437f,0.742f,0.017f,0.506f),0.001f))
	{
		logTestString("Quaternion slerp with different quaternions did not yield correct result (with t==0.5).\n");
		result = false;
	}
	q2.slerp(q,q3,0.2345f);
	if (!q2.equals(core::quaternion(-0.4202f,0.7499f,0.03814f,0.5093f),0.0007f))
	{
		logTestString("Quaternion slerp with different quaternions did not yield correct result (with t==0.2345).\n");
		result = false;
	}
	return result;
}
