newSceneView( PopupDropper* pud )
{
    scene->deleteLater();
    scene = new QGraphicsScene( pud );

    view = new PopupDropperView( pud, scene, widget );

}
