testCopy()
{
	ActiveObject activeObj;

	ActiveObject::IntIntType ii = activeObj.testMethod;
	ActiveResult<int> rii = ii(123);
	assert (!rii.available());
	activeObj.cont();
	rii.wait();
	assert (rii.available());
	assert (rii.data() == 123);
	assert (!rii.failed());

	ActiveObject::VoidIntType  vi = activeObj.testVoid;
	ActiveResult<void> rvi = vi(123);
	assert (!rvi.available());
	activeObj.cont();
	rvi.wait();
	assert (rvi.available());
	assert (!rvi.failed());

	ActiveObject::VoidVoidType vv = activeObj.testVoidInOut;
	ActiveResult<void> rvv = vv();
	assert (!rvv.available());
	activeObj.cont();
	rvv.wait();
	assert (rvv.available());
	assert (!rvv.failed());

	ActiveObject::IntVoidType  iv = activeObj.testVoidIn;
	ActiveResult<int> riv = iv();
	assert (!riv.available());
	activeObj.cont();
	riv.wait();
	assert (riv.available());
	assert (riv.data() == 123);
	assert (!riv.failed());
}
