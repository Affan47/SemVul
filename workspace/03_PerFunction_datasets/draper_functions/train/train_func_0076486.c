loadLevel(QDataStream& xcf_io, Layer& layer, qint32 bpp)
{
	qint32 width;
	qint32 height;
	quint32 offset;

	xcf_io >> width >> height >> offset;

	if (offset == 0)
		return true;

	for (uint j = 0; j < layer.nrows; j++) {
		for (uint i = 0; i < layer.ncols; i++) {

			if (offset == 0) {
				kDebug(399) << "XCF: incorrect number of tiles in layer " << layer.name;
				return false;
			}

			qint64 saved_pos = xcf_io.device()->pos();
			quint32 offset2;
			xcf_io >> offset2;


			if (offset2 == 0)
				offset2 = offset + (uint)(TILE_WIDTH * TILE_HEIGHT * 4 * 1.5);

			xcf_io.device()->seek(offset);
			int size = layer.image_tiles[j][i].width() * layer.image_tiles[j][i].height();

			if (!loadTileRLE(xcf_io, layer.tile, size, offset2 - offset, bpp))
				return false;


			layer.assignBytes(layer, i, j);

			xcf_io.device()->seek(saved_pos);
			xcf_io >> offset;
		}
	}

	return true;
}
