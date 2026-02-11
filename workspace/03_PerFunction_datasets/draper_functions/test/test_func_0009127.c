nv50_crtc_destroy(struct drm_crtc *crtc)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv50_disp *disp = nv50_disp(crtc->dev);
	struct nv50_head *head = nv50_head(crtc);
	struct nv50_fbdma *fbdma;

	list_for_each_entry(fbdma, &disp->fbdma, head) {
		nvif_object_fini(&fbdma->base[nv_crtc->index]);
	}

	nv50_dmac_destroy(&head->ovly.base, disp->disp);
	nv50_pioc_destroy(&head->oimm.base);
	nv50_dmac_destroy(&head->sync.base, disp->disp);
	nv50_pioc_destroy(&head->curs.base);


	if (head->image)
		nouveau_bo_unpin(head->image);
	nouveau_bo_ref(NULL, &head->image);


	if (nv_crtc->cursor.nvbo)
		nouveau_bo_unpin(nv_crtc->cursor.nvbo);
	nouveau_bo_ref(NULL, &nv_crtc->cursor.nvbo);

	nouveau_bo_unmap(nv_crtc->lut.nvbo);
	if (nv_crtc->lut.nvbo)
		nouveau_bo_unpin(nv_crtc->lut.nvbo);
	nouveau_bo_ref(NULL, &nv_crtc->lut.nvbo);

	drm_crtc_cleanup(crtc);
	kfree(crtc);
}
