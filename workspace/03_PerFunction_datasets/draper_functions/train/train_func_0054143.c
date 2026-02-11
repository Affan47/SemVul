horizontalRes() const
{


    return (vr == VR_NORMAL ? 204 :
	    vr == VR_FINE ? 204 :
	    vr == VR_R8 ? 204 :
	    vr == VR_R16 ? 408 :
	    vr == VR_200X100 ? 200 :
	    vr == VR_200X200 ? 200 :
	    vr == VR_200X400 ? 200 :
	    vr == VR_300X300 ? 300 :
	    (u_int) -1);
}
