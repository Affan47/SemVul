cs46xx_dsp_create_pcm_reader_scb(struct snd_cs46xx * chip, char * scb_name,
                                 u16 sample_buffer_addr, u32 dest,
                                 int virtual_channel, u32 playback_hw_addr,
                                 struct dsp_scb_descriptor * parent_scb,
                                 int scb_child_type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;

	struct dsp_generic_scb pcm_reader_scb = {


		{ DMA_RQ_C1_SOURCE_ON_HOST +
		  DMA_RQ_C1_SOURCE_MOD1024 +
		  DMA_RQ_C1_DEST_MOD32 +
		  DMA_RQ_C1_WRITEBACK_SRC_FLAG +
		  DMA_RQ_C1_WRITEBACK_DEST_FLAG +
		  15,


		  DMA_RQ_C2_AC_NONE +
		  DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG +

		  virtual_channel,
		  playback_hw_addr,
		  DMA_RQ_SD_SP_SAMPLE_ADDR +
		  sample_buffer_addr
		},

		{
			0,
			0,
			0,
			0,
			0
		},

		NULL_SCB_ADDR,NULL_SCB_ADDR,

		0,NULL_SCB_ADDR,


		RSCONFIG_DMA_ENABLE +
		(19 << RSCONFIG_MAX_DMA_SIZE_SHIFT) +

		((dest >> 4) << RSCONFIG_STREAM_NUM_SHIFT) +
		RSCONFIG_SAMPLE_16STEREO +
		RSCONFIG_MODULO_32,

		(sample_buffer_addr << 0x10),

		0,
		{


			0xffff,0xffff,
			0xffff,0xffff
		}
	};

	if (ins->null_algorithm == NULL) {
		ins->null_algorithm =  cs46xx_dsp_lookup_symbol (chip,"NULLALGORITHM",
								 SYMBOL_CODE);

		if (ins->null_algorithm == NULL) {
			dev_err(chip->card->dev,
				"dsp_spos: symbol NULLALGORITHM not found\n");
			return NULL;
		}
	}

	scb = _dsp_create_generic_scb(chip,scb_name,(u32 *)&pcm_reader_scb,
				      dest,ins->null_algorithm,parent_scb,
				      scb_child_type);

	return scb;
}
