ast_cursor_move(struct drm_crtc *crtc,
			   int x, int y)
{
	struct ast_crtc *ast_crtc = to_ast_crtc(crtc);
	struct ast_private *ast = crtc->dev->dev_private;
	int x_offset, y_offset;
	u8 *sig;

	sig = (u8 *)ast->cache_kmap.virtual + (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor + AST_HWC_SIZE;
	writel(x, sig + AST_HWC_SIGNATURE_X);
	writel(y, sig + AST_HWC_SIGNATURE_Y);

	x_offset = ast_crtc->offset_x;
	y_offset = ast_crtc->offset_y;
	if (x < 0) {
		x_offset = (-x) + ast_crtc->offset_x;
		x = 0;
	}

	if (y < 0) {
		y_offset = (-y) + ast_crtc->offset_y;
		y = 0;
	}
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc2, x_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc3, y_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc4, (x & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc5, ((x >> 8) & 0x0f));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc6, (y & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc7, ((y >> 8) & 0x07));


	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xCB, 0xFF, 0x00);

	return 0;
}
