Push(void) const
{

    Matrix().Push();


    if (IsMirrored()) {
        R3draw_mirrored = !R3draw_mirrored;
#if (RN_3D_GRFX == RN_IRISGL)
        frontface(R3draw_mirrored);
        backface(!R3draw_mirrored);
#elif (RN_3D_GRFX == RN_OPENGL)
        glFrontFace((R3draw_mirrored) ? GL_CW : GL_CCW);
#elif (RN_3D_GRFX == RN_3DR)
	G3dSetState(R3dr_gc, G3DL_FRONT_CCW, (R3draw_mirrored) ? 0 : 1);
#else
	RNAbort("Not Implemented");
#endif
    }
}
