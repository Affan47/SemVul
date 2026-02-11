efi_width ( size_t size ) {
	switch ( size ) {
	case 1 :	return EfiCpuIoWidthFifoUint8;
	case 2 :	return EfiCpuIoWidthFifoUint16;
	case 4 :	return EfiCpuIoWidthFifoUint32;
	case 8 :	return EfiCpuIoWidthFifoUint64;
	default :
		assert ( 0 );

		return EfiCpuIoWidthMaximum;
	}
}
