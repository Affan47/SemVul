vmw_so_build_asserts(void)
{

	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 1);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 2);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 3);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 4);
	BUILD_BUG_ON(SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW + 5);


	BUILD_BUG_ON(sizeof(union vmw_view_destroy) != sizeof(u32));


	BUILD_BUG_ON(SVGA_COTABLE_MAX_IDS >= ((1 << 20) - 1));


	BUILD_BUG_ON(offsetof(struct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineShaderResourceView, sid));
	BUILD_BUG_ON(offsetof(struct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineRenderTargetView, sid));
	BUILD_BUG_ON(offsetof(struct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineDepthStencilView, sid));
}
