update()
{

    BoundingBox.MinEdge = core::vector3df(MeshPosition.X*TileSize, BoundingBox.MinEdge.Y, MeshPosition.Y*TileSize);
    BoundingBox.MaxEdge = core::vector3df( (MeshPosition.X+MeshSize.Width)*TileSize, BoundingBox.MaxEdge.Y, (MeshPosition.Y+MeshSize.Height)*TileSize);

    for(s32 j=0; j<Sector.height(); j++)
        for(s32 i=0; i<Sector.width(); i++)
        {
            Sector(i,j).BoundingBox.MinEdge = core::vector3df(
                (MeshPosition.X + Sector(i,j).Offset.X) * TileSize,
                Sector(i,j).BoundingBox.MinEdge.Y,
                (MeshPosition.Y + Sector(i,j).Offset.Y) * TileSize);

            Sector(i,j).BoundingBox.MaxEdge = core::vector3df(
                (MeshPosition.X + Sector(i,j).Offset.X + Sector(i,j).Size.Width) * TileSize,
                Sector(i,j).BoundingBox.MaxEdge.Y,
                (MeshPosition.Y + Sector(i,j).Offset.Y + Sector(i,j).Size.Height) * TileSize);
        }


    for(s32 j=0; j<Sector.height(); j++)
        for(s32 i=0; i<Sector.width(); i++) Sector(i,j).UpdateTexture = true;


    for(s32 j=0; j<Sector.height(); j++)
        for(s32 i=0; i<Sector.width(); i++) Sector(i,j).UpdateVertices = true;
}
