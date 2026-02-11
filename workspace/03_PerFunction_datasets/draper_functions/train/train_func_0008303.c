intel_dvo_enc_destroy(struct drm_encoder *encoder)
{
	struct intel_dvo *intel_dvo = enc_to_dvo(to_intel_encoder(encoder));

	if (intel_dvo->dev.dev_ops->destroy)
		intel_dvo->dev.dev_ops->destroy(&intel_dvo->dev);

	intel_encoder_destroy(encoder);
}
