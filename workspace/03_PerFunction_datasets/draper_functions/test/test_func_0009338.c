initClass()


{
    SO__NODE_INIT_CLASS(SoNormal, "Normal", SoNode);


    SO_ENABLE(SoGLRenderAction, SoGLNormalElement);
    SO_ENABLE(SoCallbackAction, SoNormalElement);
    SO_ENABLE(SoPickAction,	SoNormalElement);
}
