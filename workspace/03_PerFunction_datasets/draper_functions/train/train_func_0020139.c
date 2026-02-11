average(const void* src, int sstride, int uw, int vw,
			void* dst, DataType dt, int nchan)
{
    switch (dt) {
    case dt_uint8:   ::average((const uint8_t*) src, sstride, uw, vw,
			       (uint8_t*) dst, nchan); break;
    case dt_half:    ::average((const PtexHalf*) src, sstride, uw, vw,
			       (PtexHalf*) dst, nchan); break;
    case dt_uint16:  ::average((const uint16_t*) src, sstride, uw, vw,
			       (uint16_t*) dst, nchan); break;
    case dt_float:   ::average((const float*) src, sstride, uw, vw,
			       (float*) dst, nchan); break;
    }
}
