append(Model* model)

{
    mapModels[model->key()] = model;
    if (this->setFlag == true)
        setModels.insert(model);
    this->n++;
}
