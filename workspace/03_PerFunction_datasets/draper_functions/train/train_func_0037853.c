Copy () {
    Iterator i;
    Picture* newPicture = new Picture(this);

    for (First(i); !Done(i); Next(i)) {
        newPicture->Append(GetGraphic(i)->Copy());
    }
    return newPicture;
}
