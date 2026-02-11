nv3UpdateArbitrationSettings
(
    unsigned      VClk,
    unsigned      pixelDepth,
    unsigned     *burst,
    unsigned     *lwm,
    RIVA_HW_INST *chip
)
{
    nv3_fifo_info fifo_data;
    nv3_sim_state sim_data;
    unsigned int M, N, P, pll, MClk;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000504/4], 0);
    M = (pll >> 0) & 0xFF; N = (pll >> 8) & 0xFF; P = (pll >> 16) & 0x0F;
    MClk = (N * chip->CrystalFreqKHz / M) >> P;
    sim_data.pix_bpp        = (char)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;
    sim_data.video_scale    = 1;
    sim_data.memory_width   = (NV_RD32(&chip->PEXTDEV[0x00000000/4], 0) & 0x10) ?
	128 : 64;
    sim_data.memory_width   = 128;

    sim_data.mem_latency    = 9;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = 11;
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    nv3CalcArbitration(&fifo_data, &sim_data);
    if (fifo_data.valid)
    {
        int  b = fifo_data.graphics_burst_size >> 4;
        *burst = 0;
        while (b >>= 1)
	    (*burst)++;
        *lwm   = fifo_data.graphics_lwm >> 3;
    }
    else
    {
        *lwm   = 0x24;
        *burst = 0x2;
    }
}
