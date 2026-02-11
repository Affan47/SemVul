knh_Bytes_reduce(kBytes *ba, size_t size)
{
	if(BA_size(ba) >= size) {
		BA_size(ba) -= size;
		knh_bzero(ba->bu.ubuf + BA_size(ba), size);
	}
}
