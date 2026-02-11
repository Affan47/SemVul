splitAndApply(PtexTriangleKernel& k, int faceid, const Ptex::FaceInfo& f)
{

    if (k.u1 < 0 && f.adjface(2) >= 0) {
	PtexTriangleKernel ka;
	k.splitU(ka);
	applyAcrossEdge(ka, f, 2);
    }
    if (k.v1 < 0 && f.adjface(0) >= 0) {
	PtexTriangleKernel ka;
	k.splitV(ka);
	applyAcrossEdge(ka, f, 0);
    }
    if (k.w1 < 0 && f.adjface(1) >= 0) {
	PtexTriangleKernel ka;
	k.splitW(ka);
	applyAcrossEdge(ka, f, 1);
    }

    apply(k, faceid, f);
}
