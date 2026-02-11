moveToLayer(LayerItem &item, int layernum) {

    Layer &curr_layer = item.getLayer();


    if (curr_layer.getLayerNum() == layernum)
        return;

    layernum = FbTk::Util::clamp(layernum, 0, static_cast<signed>(m_layers.size()) - 1);
    item.setLayer(*m_layers[layernum]);
}
